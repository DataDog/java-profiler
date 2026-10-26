---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:28:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 568 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792977826 96
1792977831 96
1792977836 96
1792977841 96
1792977846 96
1792977851 96
1792977856 96
1792977861 96
1792977866 96
1792977871 96
1792977876 96
1792977881 96
1792977886 96
1792977891 96
1792977896 94
1792977901 94
1792977906 94
1792977911 94
1792977916 94
1792977921 94
```
</details>

---

