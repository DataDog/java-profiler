---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-01 20:32:51 EST

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
| CPU Cores (start) | 64 |
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
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793582733 64
1793582738 64
1793582743 64
1793582748 64
1793582753 64
1793582758 64
1793582763 64
1793582768 64
1793582773 64
1793582778 64
1793582783 64
1793582788 64
1793582793 64
1793582798 64
1793582803 64
1793582808 64
1793582813 64
1793582818 64
1793582823 64
1793582828 64
```
</details>

---

