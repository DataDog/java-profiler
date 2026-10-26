---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 08:33:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793017781 28
1793017786 28
1793017791 28
1793017796 28
1793017801 28
1793017807 28
1793017812 28
1793017817 28
1793017822 28
1793017827 28
1793017832 28
1793017837 28
1793017842 28
1793017847 28
1793017852 28
1793017857 28
1793017862 28
1793017867 28
1793017872 28
1793017877 28
```
</details>

---

