---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:21:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1794824159 34
1794824164 34
1794824169 34
1794824174 34
1794824179 34
1794824184 34
1794824189 34
1794824194 34
1794824199 34
1794824204 34
1794824209 34
1794824214 34
1794824219 34
1794824224 34
1794824229 34
1794824234 34
1794824239 34
1794824244 34
1794824249 34
1794824254 34
```
</details>

---

