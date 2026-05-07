---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 13:16:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1014 |
| Sample Rate | 16.90/sec |
| Health Score | 1056% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778173726 64
1778173731 64
1778173736 64
1778173741 64
1778173746 64
1778173751 64
1778173756 64
1778173761 64
1778173766 64
1778173771 64
1778173776 64
1778173781 64
1778173786 64
1778173791 64
1778173796 64
1778173801 64
1778173806 64
1778173811 64
1778173816 64
1778173821 64
```
</details>

---

