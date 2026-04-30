---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1777558114 91
1777558119 91
1777558124 91
1777558129 91
1777558134 91
1777558139 91
1777558144 91
1777558149 93
1777558154 93
1777558159 93
1777558164 93
1777558169 93
1777558174 93
1777558179 93
1777558184 93
1777558189 93
1777558194 93
1777558199 93
1777558204 93
1777558209 93
```
</details>

---

