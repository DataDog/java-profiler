---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:23:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (5 unique values: 33-64 cores)</summary>

```
1795605526 44
1795605531 44
1795605536 60
1795605541 60
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
1795605606 64
1795605611 64
1795605616 64
1795605621 64
```
</details>

---

