---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 17:07:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 26-36 cores)</summary>

```
1795817048 36
1795817053 36
1795817058 36
1795817063 36
1795817068 36
1795817073 36
1795817078 36
1795817083 36
1795817088 36
1795817093 36
1795817098 26
1795817103 26
1795817108 26
1795817113 26
1795817118 26
1795817123 26
1795817128 36
1795817133 36
1795817138 36
1795817143 36
```
</details>

---

