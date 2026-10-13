---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 05:40:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 27-31 cores)</summary>

```
1791884117 30
1791884122 30
1791884127 30
1791884132 30
1791884137 30
1791884142 30
1791884147 30
1791884152 30
1791884157 31
1791884162 31
1791884167 31
1791884172 31
1791884177 31
1791884182 31
1791884187 31
1791884192 31
1791884197 31
1791884202 31
1791884207 29
1791884212 29
```
</details>

---

