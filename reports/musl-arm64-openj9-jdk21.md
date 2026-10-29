---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 07:57:23 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 14 |
| Allocations | 203 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1793274809 25
1793274814 25
1793274819 25
1793274824 25
1793274829 25
1793274834 25
1793274839 25
1793274844 30
1793274849 30
1793274854 30
1793274859 30
1793274864 30
1793274869 30
1793274874 30
1793274879 30
1793274884 30
1793274889 30
1793274894 30
1793274899 30
1793274904 30
```
</details>

---

