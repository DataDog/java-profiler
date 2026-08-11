---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 04:46:58 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786437768 46
1786437773 46
1786437778 46
1786437783 46
1786437788 46
1786437793 46
1786437798 46
1786437803 46
1786437808 46
1786437813 51
1786437818 51
1786437823 51
1786437828 51
1786437833 51
1786437838 51
1786437843 51
1786437848 51
1786437853 51
1786437858 51
1786437863 51
```
</details>

---

