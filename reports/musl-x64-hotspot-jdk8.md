---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-06 14:10:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 57-62 cores)</summary>

```
1778090717 60
1778090722 62
1778090728 62
1778090733 62
1778090738 62
1778090743 62
1778090748 62
1778090753 60
1778090758 60
1778090763 60
1778090768 60
1778090773 60
1778090778 60
1778090783 60
1778090788 60
1778090793 62
1778090798 62
1778090803 62
1778090808 62
1778090813 60
```
</details>

---

