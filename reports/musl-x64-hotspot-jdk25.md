---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:10:47 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 10 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 11-23 cores)</summary>

```
1778090723 11
1778090728 11
1778090733 11
1778090738 11
1778090743 11
1778090748 11
1778090753 11
1778090758 11
1778090763 11
1778090768 11
1778090773 11
1778090778 11
1778090783 11
1778090788 11
1778090793 23
1778090798 23
1778090803 23
1778090808 23
1778090813 23
1778090818 23
```
</details>

---

