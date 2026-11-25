---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:36:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795620718 64
1795620723 64
1795620728 64
1795620733 64
1795620738 64
1795620743 64
1795620748 64
1795620753 64
1795620758 64
1795620763 64
1795620768 64
1795620773 64
1795620778 64
1795620783 64
1795620788 64
1795620793 64
1795620798 64
1795620803 64
1795620808 64
1795620813 64
```
</details>

---

