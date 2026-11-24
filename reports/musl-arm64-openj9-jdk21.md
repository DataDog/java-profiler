---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 11:39:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 16 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795537829 64
1795537834 64
1795537839 64
1795537844 64
1795537849 64
1795537854 64
1795537859 64
1795537864 64
1795537869 64
1795537874 64
1795537880 64
1795537885 64
1795537890 64
1795537895 64
1795537900 64
1795537905 64
1795537910 64
1795537915 64
1795537920 64
1795537925 64
```
</details>

---

