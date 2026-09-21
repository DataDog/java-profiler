---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 17:43:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 27-31 cores)</summary>

```
1790026679 27
1790026684 27
1790026689 27
1790026694 27
1790026699 27
1790026704 27
1790026709 27
1790026714 27
1790026719 27
1790026724 27
1790026729 29
1790026734 29
1790026739 31
1790026744 31
1790026749 29
1790026754 29
1790026759 29
1790026764 29
1790026769 29
1790026774 29
```
</details>

---

