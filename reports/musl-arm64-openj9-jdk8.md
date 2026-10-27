---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-27 13:58:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1793123639 30
1793123644 30
1793123649 30
1793123654 30
1793123659 30
1793123664 30
1793123669 30
1793123674 30
1793123679 30
1793123684 30
1793123689 30
1793123694 30
1793123699 30
1793123704 30
1793123709 35
1793123714 35
1793123719 35
1793123724 35
1793123729 35
1793123734 35
```
</details>

---

