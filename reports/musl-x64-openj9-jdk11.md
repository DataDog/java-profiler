---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:40:46 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 953 |
| Sample Rate | 15.88/sec |
| Health Score | 993% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 82-87 cores)</summary>

```
1794504865 87
1794504870 87
1794504875 87
1794504880 87
1794504885 87
1794504890 87
1794504895 87
1794504900 87
1794504905 87
1794504910 87
1794504915 87
1794504920 87
1794504926 87
1794504931 87
1794504936 85
1794504941 85
1794504946 85
1794504951 84
1794504956 84
1794504961 84
```
</details>

---

