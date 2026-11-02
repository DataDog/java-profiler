---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 07:03:41 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (6 unique values: 44-64 cores)</summary>

```
1793620782 51
1793620787 51
1793620792 51
1793620797 51
1793620802 51
1793620807 51
1793620812 51
1793620817 51
1793620822 51
1793620827 49
1793620832 49
1793620837 49
1793620842 49
1793620847 49
1793620852 49
1793620857 44
1793620862 44
1793620867 57
1793620872 57
1793620877 58
```
</details>

---

