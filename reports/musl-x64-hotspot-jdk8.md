---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 66-77 cores)</summary>

```
1777558051 71
1777558056 66
1777558061 66
1777558066 73
1777558071 73
1777558076 73
1777558081 73
1777558086 73
1777558091 73
1777558097 73
1777558102 77
1777558107 77
1777558112 68
1777558117 68
1777558122 68
1777558127 70
1777558132 70
1777558137 70
1777558142 70
1777558147 70
```
</details>

---

