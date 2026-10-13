---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 08:38:35 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 27-66 cores)</summary>

```
1791894792 27
1791894797 27
1791894802 27
1791894807 27
1791894812 27
1791894818 27
1791894823 27
1791894828 27
1791894833 27
1791894838 27
1791894843 47
1791894848 47
1791894853 49
1791894858 49
1791894863 49
1791894868 49
1791894873 66
1791894878 66
1791894883 66
1791894888 66
```
</details>

---

