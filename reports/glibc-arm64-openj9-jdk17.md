---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:54:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1786974691 40
1786974696 40
1786974701 40
1786974706 40
1786974711 40
1786974716 40
1786974721 40
1786974726 40
1786974731 40
1786974736 40
1786974741 40
1786974746 40
1786974751 40
1786974756 40
1786974761 40
1786974766 40
1786974771 40
1786974776 40
1786974781 40
1786974786 43
```
</details>

---

