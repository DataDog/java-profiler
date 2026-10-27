---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:59:54 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 973 |
| Sample Rate | 16.22/sec |
| Health Score | 1014% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1793123659 33
1793123664 33
1793123669 33
1793123674 33
1793123679 33
1793123684 33
1793123689 33
1793123694 33
1793123699 33
1793123704 33
1793123709 33
1793123714 33
1793123719 33
1793123724 33
1793123729 33
1793123734 33
1793123739 33
1793123744 33
1793123749 33
1793123754 33
```
</details>

---

