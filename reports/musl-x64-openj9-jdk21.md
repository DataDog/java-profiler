---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 17:49:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792619144 32
1792619149 32
1792619154 32
1792619159 32
1792619164 32
1792619169 32
1792619174 32
1792619179 32
1792619184 32
1792619189 32
1792619194 32
1792619199 30
1792619204 30
1792619209 30
1792619214 30
1792619219 30
1792619224 30
1792619229 30
1792619234 30
1792619239 30
```
</details>

---

