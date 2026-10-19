---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 06:50:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 12 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 29-64 cores)</summary>

```
1792406780 64
1792406785 64
1792406790 64
1792406795 64
1792406800 64
1792406805 64
1792406810 29
1792406815 29
1792406820 29
1792406825 29
1792406830 29
1792406835 29
1792406840 29
1792406845 29
1792406850 29
1792406855 29
1792406860 29
1792406865 29
1792406870 29
1792406875 29
```
</details>

---

