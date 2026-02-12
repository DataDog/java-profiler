---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-12 10:15:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 13 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 59-64 cores)</summary>

```
1770908980 64
1770908985 64
1770908990 64
1770908995 64
1770909000 63
1770909005 63
1770909010 62
1770909015 62
1770909020 62
1770909025 62
1770909030 62
1770909035 62
1770909040 62
1770909045 62
1770909050 62
1770909055 62
1770909060 64
1770909065 64
1770909070 64
1770909075 64
```
</details>

---

