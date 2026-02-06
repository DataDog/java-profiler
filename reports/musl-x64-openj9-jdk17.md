---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-05 20:41:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 38-96 cores)</summary>

```
1770341747 96
1770341752 96
1770341757 96
1770341762 96
1770341767 96
1770341772 96
1770341777 96
1770341782 96
1770341787 96
1770341792 38
1770341797 38
1770341802 38
1770341807 38
1770341812 38
1770341817 38
1770341822 38
1770341827 38
1770341832 38
1770341837 38
1770341842 38
```
</details>

---

