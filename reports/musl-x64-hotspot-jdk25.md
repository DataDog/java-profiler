---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 09:28:59 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 446 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1787577802 68
1787577807 68
1787577812 68
1787577817 68
1787577822 68
1787577827 68
1787577832 68
1787577837 68
1787577842 68
1787577847 68
1787577852 68
1787577857 68
1787577862 68
1787577867 68
1787577872 68
1787577877 68
1787577882 68
1787577887 76
1787577892 76
1787577897 76
```
</details>

---

