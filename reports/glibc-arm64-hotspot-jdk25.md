---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:06:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1794848467 40
1794848472 40
1794848477 40
1794848482 40
1794848487 40
1794848492 40
1794848497 40
1794848502 40
1794848507 40
1794848512 40
1794848517 40
1794848522 40
1794848527 40
1794848532 42
1794848537 42
1794848542 42
1794848547 42
1794848552 42
1794848557 42
1794848562 42
```
</details>

---

