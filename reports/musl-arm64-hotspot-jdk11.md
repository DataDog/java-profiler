---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-16 12:11:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1002 |
| Sample Rate | 16.70/sec |
| Health Score | 1044% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789574723 48
1789574728 48
1789574733 48
1789574738 48
1789574743 48
1789574748 48
1789574753 48
1789574758 48
1789574763 48
1789574768 48
1789574773 48
1789574778 48
1789574783 48
1789574788 48
1789574793 48
1789574798 48
1789574803 48
1789574808 48
1789574813 48
1789574818 48
```
</details>

---

