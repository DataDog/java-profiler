---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 06:23:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 33-64 cores)</summary>

```
1795605505 45
1795605510 45
1795605515 45
1795605520 44
1795605525 44
1795605530 44
1795605535 60
1795605540 60
1795605546 60
1795605551 60
1795605556 60
1795605561 60
1795605566 63
1795605571 63
1795605576 63
1795605581 63
1795605586 64
1795605591 64
1795605596 64
1795605601 64
```
</details>

---

