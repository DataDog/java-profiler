---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:52:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1794498214 46
1794498219 46
1794498224 46
1794498229 46
1794498234 46
1794498239 46
1794498244 46
1794498249 46
1794498254 41
1794498259 41
1794498264 40
1794498269 40
1794498274 40
1794498279 40
1794498284 40
1794498289 40
1794498294 40
1794498299 40
1794498304 40
1794498309 40
```
</details>

---

