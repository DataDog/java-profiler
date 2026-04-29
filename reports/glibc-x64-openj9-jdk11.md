---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 11:09:01 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1777475062 60
1777475067 60
1777475072 55
1777475077 55
1777475082 55
1777475087 55
1777475092 55
1777475097 55
1777475102 60
1777475107 60
1777475112 60
1777475117 55
1777475122 55
1777475127 55
1777475132 55
1777475137 55
1777475142 55
1777475148 55
1777475153 55
1777475158 55
```
</details>

---

