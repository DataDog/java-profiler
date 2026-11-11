---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 20:36:47 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 25-34 cores)</summary>

```
1794360758 29
1794360763 29
1794360768 29
1794360773 29
1794360778 29
1794360783 29
1794360788 34
1794360793 34
1794360798 29
1794360803 29
1794360808 29
1794360813 29
1794360818 29
1794360823 29
1794360828 29
1794360833 29
1794360838 29
1794360843 29
1794360848 29
1794360853 29
```
</details>

---

