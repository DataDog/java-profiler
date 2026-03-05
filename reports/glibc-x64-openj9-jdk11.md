---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-05 15:44:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
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
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1772743232 20
1772743237 20
1772743242 20
1772743247 20
1772743252 20
1772743257 20
1772743262 20
1772743267 20
1772743272 20
1772743278 20
1772743283 20
1772743288 20
1772743293 32
1772743298 32
1772743303 32
1772743308 32
1772743313 32
1772743318 32
1772743323 32
1772743328 32
```
</details>

---

