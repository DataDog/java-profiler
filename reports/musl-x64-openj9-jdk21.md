---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 11:54:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795711795 87
1795711800 96
1795711805 96
1795711810 96
1795711815 96
1795711820 96
1795711825 96
1795711830 96
1795711835 96
1795711840 96
1795711845 96
1795711850 96
1795711855 96
1795711860 96
1795711865 96
1795711870 96
1795711875 96
1795711880 96
1795711885 96
1795711890 96
```
</details>

---

