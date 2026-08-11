---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 04:47:00 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 38-57 cores)</summary>

```
1786437744 57
1786437749 57
1786437754 57
1786437759 38
1786437764 38
1786437769 38
1786437775 38
1786437780 38
1786437785 38
1786437790 38
1786437795 38
1786437800 38
1786437805 41
1786437810 41
1786437815 41
1786437820 41
1786437825 41
1786437830 41
1786437835 41
1786437840 41
```
</details>

---

