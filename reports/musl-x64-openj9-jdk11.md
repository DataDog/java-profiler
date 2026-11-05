---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 12:01:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 583 |

<details>
<summary>CPU Timeline (3 unique values: 50-59 cores)</summary>

```
1793897752 52
1793897757 50
1793897762 50
1793897767 50
1793897772 50
1793897777 50
1793897782 50
1793897787 50
1793897792 50
1793897797 50
1793897802 50
1793897807 50
1793897812 50
1793897817 50
1793897822 50
1793897827 50
1793897832 50
1793897837 59
1793897842 59
1793897847 59
```
</details>

---

