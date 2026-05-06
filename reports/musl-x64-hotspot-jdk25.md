---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:42:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 47-52 cores)</summary>

```
1778092672 52
1778092677 52
1778092682 47
1778092687 47
1778092692 47
1778092697 47
1778092702 47
1778092707 47
1778092712 47
1778092717 47
1778092722 47
1778092727 47
1778092732 47
1778092737 47
1778092742 47
1778092747 47
1778092752 47
1778092757 47
1778092762 51
1778092767 51
```
</details>

---

