---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-05 15:44:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1772743228 32
1772743233 32
1772743238 32
1772743243 32
1772743248 32
1772743253 32
1772743258 32
1772743263 32
1772743268 32
1772743273 32
1772743278 32
1772743283 32
1772743288 32
1772743293 32
1772743298 32
1772743303 32
1772743308 32
1772743313 32
1772743318 32
1772743323 32
```
</details>

---

