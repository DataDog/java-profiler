---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:28:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1788279673 36
1788279678 36
1788279683 36
1788279688 36
1788279693 36
1788279698 36
1788279703 36
1788279708 36
1788279713 36
1788279718 36
1788279723 36
1788279728 36
1788279733 36
1788279738 36
1788279743 36
1788279748 36
1788279753 36
1788279758 34
1788279763 34
1788279768 34
```
</details>

---

