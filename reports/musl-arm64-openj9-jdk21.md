---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-18 05:35:56 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 33-35 cores)</summary>

```
1794997777 33
1794997782 33
1794997787 33
1794997792 33
1794997797 33
1794997802 35
1794997808 35
1794997813 35
1794997818 35
1794997823 35
1794997828 35
1794997833 35
1794997838 35
1794997843 35
1794997848 35
1794997853 35
1794997858 35
1794997863 35
1794997868 35
1794997873 35
```
</details>

---

