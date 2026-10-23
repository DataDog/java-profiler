---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 08:53:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1792759708 84
1792759713 84
1792759718 84
1792759723 84
1792759728 84
1792759733 84
1792759738 86
1792759743 86
1792759748 86
1792759753 86
1792759758 86
1792759763 86
1792759768 86
1792759773 86
1792759778 86
1792759783 84
1792759788 84
1792759793 84
1792759798 84
1792759804 84
```
</details>

---

