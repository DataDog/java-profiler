---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:21:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1018 |
| Sample Rate | 16.97/sec |
| Health Score | 1061% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 20-27 cores)</summary>

```
1794824139 20
1794824144 20
1794824149 20
1794824154 20
1794824159 20
1794824164 20
1794824169 20
1794824174 20
1794824179 20
1794824184 22
1794824189 22
1794824194 22
1794824199 22
1794824204 22
1794824209 22
1794824214 22
1794824219 22
1794824224 27
1794824229 27
1794824234 27
```
</details>

---

