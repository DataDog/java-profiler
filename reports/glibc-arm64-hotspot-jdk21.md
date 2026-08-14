---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 01:01:23 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786683333 32
1786683338 32
1786683343 32
1786683348 32
1786683353 32
1786683358 32
1786683363 32
1786683368 32
1786683373 32
1786683378 32
1786683383 32
1786683388 32
1786683393 32
1786683398 32
1786683403 32
1786683408 32
1786683413 32
1786683418 32
1786683423 32
1786683428 32
```
</details>

---

