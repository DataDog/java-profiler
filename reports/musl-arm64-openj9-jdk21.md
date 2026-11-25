---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795641763 33
1795641768 33
1795641773 33
1795641778 33
1795641783 33
1795641788 33
1795641793 64
1795641798 64
1795641803 64
1795641808 64
1795641813 64
1795641818 64
1795641823 64
1795641828 64
1795641833 64
1795641838 64
1795641843 64
1795641848 64
1795641853 64
1795641858 64
```
</details>

---

