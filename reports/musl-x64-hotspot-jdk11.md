---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 11:29:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1793201068 87
1793201073 87
1793201078 89
1793201083 89
1793201088 89
1793201093 89
1793201098 89
1793201103 91
1793201108 91
1793201113 91
1793201118 91
1793201123 91
1793201128 91
1793201133 91
1793201138 91
1793201143 91
1793201148 91
1793201153 91
1793201158 91
1793201163 91
```
</details>

---

