---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 00:00:38 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 44-54 cores)</summary>

```
1795409769 44
1795409774 44
1795409779 44
1795409784 44
1795409789 44
1795409794 44
1795409799 44
1795409804 44
1795409809 44
1795409814 44
1795409819 49
1795409824 49
1795409829 49
1795409834 49
1795409839 54
1795409844 54
1795409849 49
1795409854 49
1795409859 49
1795409864 54
```
</details>

---

