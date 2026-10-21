---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 10:05:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 11 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1792591295 42
1792591300 42
1792591305 42
1792591310 42
1792591315 42
1792591320 48
1792591325 48
1792591330 48
1792591335 48
1792591340 48
1792591345 48
1792591350 48
1792591355 48
1792591360 48
1792591365 48
1792591370 48
1792591375 48
1792591380 48
1792591385 48
1792591390 48
```
</details>

---

