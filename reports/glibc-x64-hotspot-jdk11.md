---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 08:52:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 61-64 cores)</summary>

```
1793278085 62
1793278090 62
1793278095 62
1793278100 62
1793278105 64
1793278110 64
1793278115 64
1793278120 64
1793278125 64
1793278130 64
1793278135 64
1793278140 64
1793278145 64
1793278150 64
1793278155 64
1793278160 64
1793278165 64
1793278170 64
1793278175 64
1793278180 64
```
</details>

---

