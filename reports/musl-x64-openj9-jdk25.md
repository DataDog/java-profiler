---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1793812777 76
1793812782 76
1793812787 76
1793812792 76
1793812797 76
1793812802 76
1793812807 76
1793812812 76
1793812817 76
1793812822 76
1793812827 76
1793812832 76
1793812837 76
1793812842 76
1793812847 74
1793812852 74
1793812857 74
1793812862 74
1793812867 74
1793812872 74
```
</details>

---

