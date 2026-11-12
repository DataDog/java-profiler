---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:41:14 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 9-30 cores)</summary>

```
1794486997 11
1794487002 11
1794487007 11
1794487012 11
1794487017 11
1794487022 11
1794487027 11
1794487032 11
1794487037 11
1794487042 11
1794487047 11
1794487052 11
1794487057 11
1794487062 9
1794487067 9
1794487072 9
1794487077 9
1794487082 9
1794487087 9
1794487092 9
```
</details>

---

