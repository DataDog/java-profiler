---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 74-77 cores)</summary>

```
1793812757 77
1793812762 77
1793812767 77
1793812772 77
1793812777 77
1793812782 77
1793812788 77
1793812793 74
1793812798 74
1793812803 74
1793812808 74
1793812813 74
1793812818 74
1793812823 74
1793812828 74
1793812833 74
1793812838 74
1793812843 74
1793812848 74
1793812853 74
```
</details>

---

