---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 04:51:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 60-96 cores)</summary>

```
1786006052 70
1786006057 70
1786006062 70
1786006067 70
1786006072 70
1786006077 70
1786006082 70
1786006087 96
1786006092 96
1786006097 96
1786006102 96
1786006107 96
1786006112 96
1786006117 96
1786006122 96
1786006127 96
1786006132 96
1786006137 96
1786006142 96
1786006147 96
```
</details>

---

