---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-11 04:46:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1786437768 10
1786437773 10
1786437778 10
1786437783 10
1786437788 10
1786437793 10
1786437798 10
1786437803 10
1786437808 10
1786437813 10
1786437818 10
1786437823 10
1786437828 10
1786437833 10
1786437838 10
1786437843 10
1786437848 10
1786437853 30
1786437858 30
1786437863 30
```
</details>

---

