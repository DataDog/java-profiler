---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:48:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 31-45 cores)</summary>

```
1795095803 31
1795095808 31
1795095813 45
1795095818 45
1795095823 45
1795095828 45
1795095833 45
1795095838 45
1795095843 45
1795095848 45
1795095853 45
1795095858 45
1795095863 45
1795095868 45
1795095873 45
1795095878 45
1795095883 45
1795095888 45
1795095893 44
1795095898 44
```
</details>

---

