---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:22:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 10 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857149 64
1777857154 64
1777857159 64
1777857164 64
1777857169 64
1777857174 64
1777857179 64
1777857184 64
1777857189 64
1777857194 64
1777857199 64
1777857204 64
1777857209 64
1777857214 64
1777857219 64
1777857225 64
1777857230 64
1777857235 64
1777857240 64
1777857245 64
```
</details>

---

