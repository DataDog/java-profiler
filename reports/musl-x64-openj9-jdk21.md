---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 18:22:10 EDT

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
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1000 |
| Sample Rate | 16.67/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 87-96 cores)</summary>

```
1778537945 87
1778537950 92
1778537955 92
1778537960 92
1778537965 92
1778537970 92
1778537975 92
1778537980 92
1778537985 92
1778537990 92
1778537995 92
1778538000 92
1778538005 92
1778538010 92
1778538015 96
1778538020 96
1778538025 96
1778538030 96
1778538035 96
1778538040 96
```
</details>

---

